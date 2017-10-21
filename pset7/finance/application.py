from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():

        cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        spread = db.execute("SELECT * FROM portfolio WHERE user_id = :id", id = session["user_id"])
        grouped = db.execute("SELECT symbol, SUM(shares) FROM portfolio WHERE user_id= :id GROUP BY symbol ORDER BY symbol", id=session["user_id"])

        name=[]
        price=[]
        for i in range(len(grouped)):
            namice = lookup(grouped[i]["symbol"])
            name.append(namice["name"])
            price.append(namice["price"])
        total_price = []

        for i in range(len(grouped)):
            total_price.append(usd(float(grouped[i]["SUM(shares)"]) * float(price[i])))

        fprice=[]
        for i in range(len(price)):
            fprice.append(usd(float(price[i])))

        before = 0
        after = 0
        for i in range(len(spread)):
            dictionary = lookup(spread[i]["symbol"])
            after = after + float(spread[i]["shares"]) * float(dictionary["price"])

        for i in range(len(spread)):
            before = before + float(spread[i]["shares"]) * float(spread[i]["price"])

        total = 10000.0 - before + after
        return render_template("index.html",\
        name=name, price=fprice, symare=grouped, length=len(grouped), total_price=total_price, total=usd(total), cash=usd(cash[0]["cash"]))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""

    from datetime import datetime
    d = datetime.now()
    time = d.strftime('%m/%d/%Y %H:%M:%S')

    if request.method == "POST":
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("Please fill all the fields")
        if int(request.form.get("shares")) < 1:
            return apology("Invalid shares")

        stock_data = lookup(request.form.get("symbol"))
        if not stock_data:
            return apology("Unvalid symbol")

        user_data = db.execute("SELECT * FROM users WHERE id=:user_id", user_id=session["user_id"])
        total_price = float(stock_data["price"]) * float(request.form.get("shares"))

        if total_price > user_data[0]["cash"]:
            return apology("Not Affordable")

        db.execute("INSERT INTO portfolio (user_id, symbol, price, shares, time) VALUES(:id, :symbol, :price, :shares, :time)", \
        id=session["user_id"], symbol=stock_data["symbol"], price=stock_data["price"], shares=request.form.get("shares"), time=time)

        db.execute("UPDATE users SET cash = cash - :total_price WHERE id = :id", total_price=total_price, id=session["user_id"])
        flash("Bought!")
        return redirect(url_for("index"))

    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    data = db.execute("SELECT * FROM portfolio WHERE user_id=:id", id=session["user_id"])

    return render_template("history.html", data=data, l=len(data))

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            flash('Invalid Credentials!')
            return redirect(url_for("login"))

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        flash('You were successfully logged in!')
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    flash("You successfully logged out")
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not lookup(request.form.get("symbol")):
            return apology("Unvalid Symbol")

        quote = lookup(request.form.get("symbol"))

        return render_template("quoted.html", data=quote)

    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    #forget any user_id
    session.clear()

    if request.method == "POST":

        if not request.form.get("username") or not request.form.get("password") or not request.form.get("new_password"):
            return apology("Please fill all the Fields!")
        elif request.form.get("password") != request.form.get("new_password"):
            return apology("Both Password fields should be same")

        if len(request.form.get("password")) < 8:
            return apology("Password is too small")

        hash = pwd_context.encrypt(request.form.get("password"))
        result = db.execute("INSERT into users (username, hash) VALUES(:username, :hash)", username=request.form.get("username"), hash=hash)

        if not result:
            return apology("Username already exist!")
        rows = db.execute("Select * From users WHERE username=:username", username=request.form.get("username"))

        session["user_id"] = rows[0]["id"]
        flash("Registered successfully")
        return redirect(url_for("index"))
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":

        from datetime import datetime
        d = datetime.now()
        time = d.strftime('%m/%d/%Y %H:%M:%S')

        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("Please fill all the fields")

        if int(request.form.get("shares")) < 1:
            return apology("Invalid shares")

        stock_data = lookup(request.form.get("symbol"))
        if not stock_data:
            return apology("Unvalid symbol")

        grouped = db.execute("SELECT symbol, SUM(shares) FROM portfolio WHERE user_id= :id GROUP BY symbol ORDER BY symbol", id=session["user_id"])
        i=0
        while not grouped[i]["symbol"] == stock_data["symbol"]:
            i+=1
        if grouped[i]["SUM(shares)"] < int(request.form.get("shares")):
            return apology("You don't own that much share")

        user_data = db.execute("SELECT * FROM users WHERE id=:user_id", user_id=session["user_id"])
        total_price = float(stock_data["price"]) * float(request.form.get("shares"))

        shares = - int(request.form.get("shares"))
        db.execute("INSERT INTO portfolio (user_id, symbol, price, shares, time) VALUES(:id, :symbol, :price, :shares, :time)", \
        id=session["user_id"], symbol=stock_data["symbol"], price=stock_data["price"], shares=shares, time=time)

        db.execute("UPDATE users SET cash = cash + :total_price WHERE id = :id", total_price=total_price, id=session["user_id"])
        flash("Sold!")
        return redirect(url_for("index"))
    else:
        return render_template("sell.html")

@app.route("/change_pass", methods=["POST", "GET"])
@login_required
def change_pass():

    if request.method == "GET":
        return render_template("password.html")

    else:
        if not request.form.get("old") or not request.form.get("new") or not request.form.get("confirm"):
            return apology("Please fill all the fields")
        if request.form.get("confirm") != request.form.get("new"):
            return apology("Both the password fields should be same")
        if len(request.form.get("new")) < 8:
            return apology("Password is to short")
        if request.form.get("old") == request.form.get("new"):
            return apology("Use new Password")

        rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])

        # ensure username exists and password is correct
        if pwd_context.verify(request.form.get("old"), rows[0]["hash"]):
            hashed = pwd_context.encrypt(request.form.get("new"))
            db.execute("UPDATE users SET hash = :hashed WHERE id=:id", hashed=hashed, id=session["user_id"] )
        else:
            return apology("Invalid password")
        flash("Your password has been changed successfully")
        return redirect(url_for("index"))

@app.route("/selhistory", methods = ["GET"])
@login_required
def selhistory():

    data = db.execute("SELECT * FROM portfolio WHERE user_id=:id", id=session["user_id"])
    return render_template("selhistory.html", data=data, l=len(data))