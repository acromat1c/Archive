import time

def isFloat(number):
    try:
        float(number)
        return True
    except ValueError:
        return False

def response(toWhat, iritation):
    if (toWhat == "hight"):
        if (iritation == 0):
            response  = "Human, plaese input you hight in M: "
        elif (iritation <= 3):
            response  = "Human, please try again: "
        elif (iritation <= 6):
            response  = "Human, please stop: "
        elif (iritation == 7):
            response  = "Human!?!?!?!?, I NEED TO KNOW YOUR HIGHT!!! SO PLEASE COOPERATE: "
        elif (iritation == 8):
            response  = "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░▓▓▓▓▓░░░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒░░░░▒░▒░░░░░░▒▒▒░░▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░▓░░░░░░░▓░░░▓▓▓░░░░░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░▓░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\nHuman, this is getting anoying: "
        elif (iritation == 9):
            response  = "Why do you hurt me?: "
        elif (iritation == 10):
            response  = "Human. I am god: "
        elif (iritation == 11):
            response  = ""
        elif (iritation == 12):
            response  = "ok im not... but what if i was?"
        else:
            response  = "...: "

    elif (toWhat == "weight"):
        if (iritation == 0):
            response  = "Human, please input you weight in KG: "
        elif (iritation <= 3):
            response  = "Human, please try again: "
        elif (iritation <= 6):
            response  = "Human, please stop: "
        elif (iritation == 7):
            response  = "you should hit the gym: "
        elif (iritation == 8):
            response  = "lose some weight: "
        elif (iritation == 9):
            response  = "become stronger: "
        elif (iritation == 10):
            response  = "get a girlfriend: "
        elif (iritation == 11):
            response  = "or...: "
        elif (iritation == 12):
            response  = "you can remain a loser: "
        else:
            response  = "...: "

    return response

def start():
    print("launching BMi.os")
    time.sleep(5)
    print("$ head -20 /var/log/boot.log")
    print("Scanning for Btrfs filesystems")
    print("resume: libgcrypt version: 1.5.3")
    print("[e4rat-preload] Open /var/lib/e4rat/startup.log ... ")
    print("[e4rat-preload] 6693 files scanned")
    print("[e4rat-preload] Pre-loading I-Nodes ...")
    print("[e4rat-preload] Execute `/sbin/init' ...")
    print("[e4rat-preload] Pre-loading file content ...")
    print("INIT: version 2.88 booting")
    print("[info] Using makefile-style concurrent boot in runlevel S.")
    print("[e4rat-preload] Successfully transferred files into page cache")
    print("[ ok ] Reading early boot files....")
    print("[ ok ] Starting the hotplug events dispatcher: udevd.")
    print("[ ok ] Synthesizing the initial hotplug events...done.")
    print("[ ok ] Waiting for /dev to be fully populated...done.")
    print("[ ok ] Activating swap...done.")
    print("[....] Checking root file system...fsck from util-linux 2.20.1")
    print("/dev/sda7: clean, 581416/4505600 files, 6554372/18013696 blocks")
    print("done.")
    print("[ ok ] Activating lvm and md swap...done.")
    print("[....] Checking file systems...fsck from BMi 2.20.1")

    time.sleep(3)

    print("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░")
    print("░░░▓▓▓▓▓▓▓▓░░░░░░░░░░░░░░░░░░░░░░░▓▓▓░░░░░░")
    print("░░░▓▓░░░░░▓▓░░░░▓▓▓▓░░░░░░▓▓▓▓░░░░▓▓▓░░░░░░")
    print("░░░▓▓░░░░░▓▓░░░░▓▓▓▓▓░░░░▓▓▓▓▓░░░░░░░░░░░░░")
    print("░░░▓▓▓▓▓▓▓▓░░░░░▓▓░▓▓▓░░▓▓▓░▓▓░░░░▓▓▓░░░░░░")
    print("░░░▓▓░░░░░▓▓░░░░▓▓░░▓▓▓▓▓▓░░▓▓░░░░▓▓▓░░░░░░")
    print("░░░▓▓░░░░░▓▓░░░░▓▓░░░▓▓▓▓░░░▓▓░░░░▓▓▓░░░░░░")
    print("░░░▓▓▓▓▓▓▓▓▓░░░░▓▓░░░░░░░░░░▓▓░░░░▓▓▓░░░░░░")
    print("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░")
    print()


def BMiOS():
    iritation = 0
    while True:
        hight = input(response("hight", iritation))
        if (isFloat(hight)):
            break
        else:
            iritation += 1
    iritation = 0
    while True:
        weight = input(response("weight", iritation))
        if (isFloat(weight)):
            break
        else:
            iritation += 1
    print("prossesing...")
    time.sleep(10)
    bmi = float(weight)/float(hight)**2
    print()
    print("you bmi is ", bmi, ".")

start()
BMiOS()