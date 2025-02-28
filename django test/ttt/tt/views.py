from django.shortcuts import render

# Create your views here.
from .models import Question, Choice

def index(request):
    latest_question_list = Question.objects.order_by("-pub_date")[:5]
    context = {"latest_question_list": latest_question_list}
    return render(request, "tt/index.html", context)

def detail(request, id):
    try:
        question = Question.objects.get(pk=id)
    except:
        raise Http404("question not found OwQ")
    return render(request, "tt/detail.html", {"question":question})

def results(request, id):
    try:
        question = Question.objects.get(pk=id)
    except:
        raise Http404("question not found OwQ")
    return render(request, "tt/results.html",{"question":question})