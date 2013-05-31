from django.shortcuts import render
from django.http import HttpResponse
from django.utils import simplejson
from django import forms
from django.contrib.auth.decorators import login_required
from itertools import chain

from DNAStorage.models import Specimen, FastaFiles
from DNAStorage import StorageRequestHandler


def index(request):
    specimens = Specimen.objects.exclude(Name="businesscard")
    tree = StorageRequestHandler.GetTreeList(request.user)
    context = {'specimens': specimens, 'tree': tree}
    return render(request, 'index.html', context)


class uploadFileForm(forms.Form):
    availability = None  # TODO: Find out how to bring in the two radio buttons
    # kingdomName = forms.CharField()  # TODO: Change these char fields to fix what ever Marshall does for the taxonomy selection
    # className = forms.CharField()
    # genusName = forms.CharField()
    # speciesName = forms.CharField()
    specimenName = forms.CharField()
    genomeName = forms.CharField(required=False)
    source = forms.CharField(required=False)
    dateSequenced = forms.DateTimeField(required=False)
    description = forms.CharField(required=False)
    file = forms.FileField()

@login_required
def Upload(request):
    status = None
    message =""
    if request.is_ajax() or request.method == 'POST':
        # form = uploadFileForm(request.POST, request.FILES)
        if request.method == 'POST':
            genomeInfo = {
                            'kingdom':request.POST.get('Kingdom',u''),
                            'class':request.POST.get('Class',None),
                            'genus':request.POST.get('Genus',None),
                            'species':request.POST.get('Species',None),
                            'specimen':request.POST.get('specimenName',"Unknown"),
                            'genomeName':request.POST.get('genomeName',None),
                            'source':request.POST.get('source',None),
                            'dateSequenced':request.POST.get('dateSequenced',None),
                            'description':request.POST.get('description',None),
                            'isPublic':request.POST.get('isPublic',False)
                        }
            filePath = StorageRequestHandler.HandleUploadedFile(request.FILES['file'],genomeInfo,request.user)
        uploads = StorageRequestHandler.GetUserImports(request.user).distinct()
        return render(request, 'uploadStatus.json', {'uploads':uploads}, content_type="application/json")
    context = {'status':status,'message':message,'existingSpecimens':StorageRequestHandler.GetTreeList(request.user)}
    return render(request, 'upload.html', context)


def taxonomy(request):
    json = "currentTaxonomy = " + simplejson.dumps(StorageRequestHandler.GetTreeList())
    return HttpResponse(json, content_type="application/json")