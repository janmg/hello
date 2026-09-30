from flask import Flask, Response

app = Flask(__name__)

css_content = "#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: #000000;font-size: 40px; }"

@app.route('/')
def hello():
    return '''<!DOCTYPE html>
<html>
<head>
    <style>#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: #000000;font-size: 40px; }</style>
</head>
<body>
    <div id='main'>Hello, World! ... brought to you by Flask</div>
</body>
</html>'''

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
