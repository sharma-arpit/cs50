from passlib.apps import custom_app_context

hash = custom_app_context.encrypt("arpitsharma")

print(hash)