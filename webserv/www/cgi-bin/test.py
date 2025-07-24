#!/usr/bin/python3
import os
print("Content-Type: text/html\r\n\r\n")
print("<html><body><h1>Hello from Python CGI!</h1>")
visit_count = os.getenv("VISIT_COUNT", "0")
print(f"<p>Visit count: {visit_count}</p></body></html>")