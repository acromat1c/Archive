from django.contrib import admin

# Register your models here.
from .models import Question, Choice

admin.site.site_header = "tt admin"
admin.site.site_title = "tt admin area"
admin.site.index_title = "tt admin index"


# admin.site.register(Question)
# admin.site.register(Choice)

class ChoiceInline(admin.TabularInline):
    model = Choice
    extra = 3

class QuestionAdmin(admin.ModelAdmin):
    fieldsets = [(None,{"fields":["question_text"]}),("Date information",{"fields":["pub_date"], "classes": ["collapse"]}),]
    inlines = [ChoiceInline]

admin.site.register(Question,QuestionAdmin)