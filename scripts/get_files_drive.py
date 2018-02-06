#! /usr/bin/python3

import requests
url = "https://docs.google.com/spreadsheets/d/e/2PACX-1vQqXctLu711Q9bXUpL_F5l1uKdA7ABvwzl0spgPtdrolrolUAO48RKTvDMY8beJd4PDass4wHWU2r8v/pub?output=ods"

request_file = requests.get(url)
open("files.ods", "wb").write(request_file.content)
