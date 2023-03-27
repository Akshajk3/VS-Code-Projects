from instagrapi import Client

with open("credentials.txt", "r") as f:
    username, password = f.read().splitlines()

client = Client()
client.login(username, password)

hashtag = "steak"

medias = client.hastag_medias_recent(hashtag, 20)

for i, media in enumerate(medias):
    client.media_like(media.id)