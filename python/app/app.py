from audioop import reverse
from collections import Counter
from flask import Flask, render_template, request, redirect, url_for
from turbo_flask import Turbo


app = Flask(__name__)
turbo = Turbo(app)


@app.route("/", methods=["GET", "POST"])
def index():
    TravleMachine = request.form.get("CBar")
    if TravleMachine:
        if TimeTravle(TravleMachine):
            return TimeTravle(TravleMachine)
    return render_template("index.html", path="/")

@app.route("/DrakMode", methods=["GET", "POST"])
def indexDark():
    TravleMachine = request.form.get("CBar")
    if TravleMachine:
        if TimeTravle(TravleMachine):
            return TimeTravle(TravleMachine)
    return render_template("indexDark.html", path="/DrakMode")

def TimeTravle(TravleMachine):
    path = "static/data/GlobalSearchHistory.txt"
    if TravleMachine != "":
        file1 = open(path, "a")
        file1.write(TravleMachine + "\n")
        file1.close()
    def TimeGenerator(what, where):
        if what in TravleMachine:
            return where
    TravleMachine = TravleMachine.lower()
    whereto = ""
    if not whereto: whereto = TimeGenerator("help", "Help")
    if not whereto: whereto = TimeGenerator("light mode", "index")
    if not whereto: whereto = TimeGenerator("dark mode", "indexDark")
    if not whereto: whereto = TimeGenerator("blue paint", "TheHallOfCheese")
    if not whereto: whereto = TimeGenerator("i am", "KKK")
    if not whereto: whereto = TimeGenerator("daniel simen", "MovieTheaterBackRooms")
    if not whereto: whereto = TimeGenerator("are u", "BigMistake")
    if not whereto: whereto = TimeGenerator("lets chat", "TheTalkingRoom")
    if not whereto: whereto = TimeGenerator("devils dont cry", "DMC3")
    if not whereto: whereto = TimeGenerator("double d", "NumberFile")
    if not whereto: whereto = TimeGenerator("boycott hogwarts legacy", "ChamberOfSecrets")
    if not whereto: whereto = TimeGenerator("paco paco", "TICT")
    if not whereto: whereto = TimeGenerator("rosted duck", "Ducktales")
    if not whereto: whereto = TimeGenerator("study study study", "GoldenBoy")
    if whereto: return redirect(url_for(whereto))


def PlaybackTemplate(HTML, path, MinEpisodes, MaxEpisodes):
    Episode = MinEpisodes
    if request.args.get("Episode"):
        if int(request.args.get("Episode")) >= MinEpisodes and int(request.args.get("Episode")) <= MaxEpisodes:
            Episode = request.args.get("Episode")
    try:
        file1 = open(path, "r")
    except:
        file1 = open(path, "x")
        file1.close()
    else:
        file1.close()
    if request.form.get("Comment"):
        if request.form.get("Comment") != "":
            file1 = open(path, "a")
            file1.write(request.form.get("Comment") + "\n")
            file1.close()
    file1 = open(path, "r")
    Comments = file1.readlines()
    for Comment in Comments:
        Comment = Comment.replace("<", "&lt;")
        Comment = Comment.replace(">", "&gt;")
    Comments.reverse()
    file1.close
    return render_template(HTML, Episode = Episode, Comments = Comments, MinEpisodes = MinEpisodes, MaxEpisodes = MaxEpisodes)

@app.route("/Help")
def Help():
    return render_template("Help.html")

@app.route("/TheHallOfCheese")
def TheHallOfCheese():
    return render_template("TheHallOfCheese.html")

@app.route("/MovieTheater")
def MovieTheater():
    return render_template("MovieTheater.html")

@app.route("/KKK")
def KKK():
    return render_template("KKK.html")

@app.route("/MovieTheaterBackRooms")
def MovieTheaterBackRooms():
    return render_template("MovieTheaterBackRooms.html")

@app.route("/BigMistake")
def BigMistake():
    return render_template("BigMistake.html")

@app.route("/MGS1")
def MGS1():
    return render_template("MGS1.html")
@app.route("/MGS2")
def MGS2():
    return render_template("MGS2.html")
@app.route("/MGS3")
def MGS3():
    return render_template("MGS3.html")

@app.route("/RealRTCW")
def RealRTCW():
    return render_template("RealRTCW.html")

@app.route("/DMC3")
def DMC3():
    return render_template("DMC3.html")

@app.route("/TheTalkingRoom", methods=["GET", "POST"])
def TheTalkingRoom():
    ServerID = request.form.get("ServerID")
    Username = request.form.get("Username")
    MessageBar = request.form.get("MessageBar")
    if ServerID != None and Username != None and MessageBar != None and Username != "" and MessageBar != "":
        Username = Username.replace("<", "&lt;")
        Username = Username.replace(">", "&gt;")
        if "/$" in Username and ServerID == "X5":
            Message = "<p class='Username' style='color:#10FF10'>" + "_" + Username + "</p>" + MessageBar
        else:
            MessageBar = MessageBar.replace("<", "&lt;")
            MessageBar = MessageBar.replace(">", "&gt;")
            Message = "<p class='Username'>" + "_" + Username + "</p>" + "<p class='Message'>" + MessageBar + "</p>"
        turbo.push(turbo.append(Message, "MessageBoard"))
    return render_template("TheTalkingRoom.html")

@app.route("/NumberFile", methods=["GET", "POST"])
def NumberFile():
    path = "static/data/Number.txt"
    file1 = open(path, "r")
    CurrentNumber = file1.read()
    file1.close
    if request.form.get("Plus"):
        file1 = open(path, "r+")
        numread = file1.read()
        num = 0
        if numread.isdigit():
            num = int(numread)
            num += 1
        numread = str(num)
        file1 = open(path, "w+")
        file1.write(numread)
        CurrentNumber = numread
        file1.close()
    return render_template("NumberFile.html", CurrentNumber=CurrentNumber)

@app.route("/ChamberOfSecrets", methods=["GET", "POST"])
def ChamberOfSecrets():
    path = "static/data/PeoplesSecrets.txt"
    if request.form.get("Secrets"):
        if request.form.get("Secrets") != "":
            file1 = open(path, "a")
            file1.write("\n" + request.form.get("Secrets"))
            file1.close()
    file1 = open(path, "r")
    SecretsPreview = file1.readlines()
    for Secrets in SecretsPreview:
        Secrets = Secrets.replace("<", "&lt;")
        Secrets = Secrets.replace(">", "&gt;")
    SecretsPreview.reverse()
    file1.close
    return render_template("ChamberOfSecrets.html", SecretsPreview = SecretsPreview)

@app.route("/TICT", methods=["GET", "POST"])
def TICT():
    return PlaybackTemplate("TICT.html", "static/data/TICTComments.txt", 1, 26)

@app.route("/Ducktales", methods=["GET", "POST"])
def Ducktales():
    return PlaybackTemplate("Ducktales.html", "static/data/DucktalesComments.txt", 1, 100)

@app.route("/GoldenBoy", methods=["GET", "POST"])
def GoldenBoy():
    return PlaybackTemplate("GoldenBoy.html", "static/data/GoldenBoyComments.txt", 1, 6)