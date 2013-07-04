import httplib, urllib
params = urllib.urlencode({'message': '{"session" : 12524, "type" : 1, "information" : "aaaa"}'})
headers = {"Content-type": "application/x-www-form-urlencoded",
    "Accept": "text/plain"}
conn = httplib.HTTPConnection("127.0.0.1:8080")
#conn.request("GET", "/the_chat.html");
conn.request("POST", "/chat/post", params, headers)
print "send request ok"
response = conn.getresponse()
print response.status, response.reason
print response.getheaders()
data = response.read()
print "data is ", data
conn.close()
