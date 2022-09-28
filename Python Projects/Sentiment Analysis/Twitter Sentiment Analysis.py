from textblob import TextBlob
import tweepy
import sys

mykeys = open('twitterkeys.txt', 'r').read().splitlines()

api_key = '0ibLz13yKXS6jQP1mRlyhOClA'
api_key_secret = 'Tj3WRMUeUVuV80rhb6KWeYDNdrmZkNRZqZ5CVHor7UbVXUWqIF'
access_token = '1513699468142542849-iUt8n6kY0WCtb6B6uWOtIL4Yi9qlNa'
access_token_secret = 'eLUjYXEDhTvm8gMfTWXoUMD0Lehbs124nxIX5eEMOgSH0'

auth_handler = tweepy.OAuthHandler(consumer_key=api_key, consumer_secret=api_key_secret)
auth_handler.set_access_token(access_token, access_token_secret)