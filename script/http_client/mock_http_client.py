import httplib, urllib
params = urllib.urlencode({'@message': '12524'})
headers = {"Content-type": "application/x-www-form-urlencoded",
    "Accept": "text/plain"}
conn = httplib.HTTPConnection("127.0.0.1:8080")
#conn.request("GET", "/the_chat.html");
conn.request("POST", "/chat/post", params, headers)
response = conn.getresponse()
print response.status, response.reason
print response.getheaders()
data = response.read()
print "data is ", data
conn.close()
