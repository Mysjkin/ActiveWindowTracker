from flask import Flask, request, jsonify
from flask_cors import CORS
app = Flask(__name__)
CORS(app)

@app.route('/add_entry', methods=['POST'])
def add_entry():
    if request.method == 'POST':
        print(request.json)
        #print(request.remote_addr)
        return jsonify(request.json)

if __name__=='__main__':
    app.run()