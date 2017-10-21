from flask import Flask, redirect, render_template, request, url_for, flash
import sys, os, helpers, requests
from analyzer import Analyzer
from termcolor import colored
from bs4 import BeautifulSoup

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)
    if tweets == None:
        sys.exit(colored("Unexpected error!", "red"))

    positive, negative, neutral = 0.0, 0.0, 0.0

    for tweet in tweets:
        score = analyzer.analyze(tweet)
        if score < 0.0:
            negative +=1.0
        elif score > 0.0:
            positive += 1.0
        else:
            neutral += 1.0


    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)

@app.route("/arpit")
def profile():
    return render_template("arpit.html")

@app.route("/myhomepage")
def home():
    return render_template("myhomepage.html")

@app.route("/quora")
def quora():
    return render_template("quora.html")

@app.route("/football")
def football():
    return render_template("game.html")

@app.route("/result")
def result():
        res = []
        stats = []
        game_id = request.args.get("game_id")
        url = "http://www.espn.in/football/matchstats?gameId="+game_id
        r = requests.get(url)
        soup = BeautifulSoup(r.content, 'lxml')
        score = soup.find_all("div", {"class":"score-container"})
        status = soup.find("span", {"class":"game-time"})
        names = soup.find_all("span", {"class":"team-name"})
        possesion = soup.find_all("span", {"class":"chartValue"})
        shots = soup.find_all("span", {"data-stat":"shotsSummary"})
        saves = soup.find_all("td", {"data-stat":"saves"})
        fouls = soup.find_all("td", {"data-stat":"foulsCommitted"})
        corner = soup.find_all("td", {"data-stat":"wonCorners"})
        offside = soup.find_all("td", {"data-stat":"offsides"})
        yellow = soup.find_all("td", {"data-stat":"yellowCards"})
        red = soup.find_all("td", {"data-stat":"redCards"})
        stats = [shots, fouls, corner, offside, yellow, red, saves]
        if len(stats[0]) == 0:
            return redirect(url_for("football"))
        res = [names, score, possesion]
        status = status.text.strip()
        for stat in stats:
            for i in range(2):
                stat[i] = stat[i].text.strip()
        for r in res:
            for j in range(2):
                r[j] = r[j].text.strip()
        l = ["Shots", "Corner", "Offside", "Fouls", "Yellow", "Red", "Saves"]
        return render_template("result.html", stats=stats, res=res, l=l, status=status)