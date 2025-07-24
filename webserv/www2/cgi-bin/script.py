#!/usr/bin/env python3
import sys
print("Content-Type: text/html\r\n\r\n")
print("<h1>Hello from Python!</h1>")
body = sys.stdin.read()
print(f"<p>Received body: {body}</p>")
