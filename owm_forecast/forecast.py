#!/usr/bin/env python3
# forecast.py
import argparse
import requests
import pytz
from datetime import datetime
from json import loads


def query_owm(owm, query):
    return owm[query]


def convert_unix(ts, tz, f):
    return datetime.fromtimestamp(ts, pytz.timezone(tz)).strftime(f)


def fetch_geo_data():
    response = requests.get('https://ipinfo.io/geo')
    geo = loads(response.content)

    loc = geo['loc'].split(",")
    coords = {
            'latitude': loc[0],
            'longitude': loc[1],
            'location': f"{geo['city']}/{geo['region']}"
    }

    return coords


def fetch_owm_data(coords):
    LAT = coords.get('latitude')
    LON = coords.get('longitude')
    OWM_API_KEY = '6e7e311acd7183db50a3a8cc3d187d67'
    URL = f'https://api.openweathermap.org/data/2.5/onecall?lat={LAT}&lon={LON}&appid={OWM_API_KEY}&units=metric'

    response = requests.get(URL)
    return loads(response.content)


def extract_weather(owm, query):
    output = {}
    if query in owm:
        for idx in owm[query]:
            if idx == "weather":
                if set(['main', 'description']).issubset(idx):
                    output.update({'main': idx['main']})
                    output.update({'description': idx['description']})

    return output


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
            prog='forecast',
            description='Open Weather Map forecast app')
    parser.add_argument('-v', '--verbose', action='store_true',
                        help='be verbose in forecast output')
    parser.add_argument('-b', '--brief', action='store_true',
                        help='display a brief forecast for the entire day')

    args = parser.parse_args()

    # get location and then fetch OWM data
    geo = fetch_geo_data()
    owm_raw = fetch_owm_data(geo)

    dc = u'\u2103'
    c_weather = extract_weather(owm_raw, 'current')
    h_weather = extract_weather(owm_raw, 'hourly')
    time = convert_unix(owm_raw['current']['dt'],
                        query_owm(owm_raw, 'timezone'),
                        '%A %w %B %Y at %I:%M %p')

    if args.verbose:  # verbose
        print(f"Weather forecast for {geo.get('location')}")
        print(f"{time}\n")
        print(f"Currently: {owm_raw['current']['temp']}{dc}\tFeels Like:{owm_raw['current']['feels_like']}{dc}")
        print(f"{c_weather}")
    elif args.brief and not args.verbose:  # brief
        print(f"Feels Like: {current['feels_like']}{dc}")
    else:  # default
        print(f"{current['temp']}{dc}")

