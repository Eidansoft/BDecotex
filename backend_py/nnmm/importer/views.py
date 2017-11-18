# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render

# Create your views here.
from forms import ImportForm


def mdbimport(request):

    if request.method == 'POST':
        form = ImportForm(request.POST, request.FILES)
        if form.is_valid():
            pass
            #handle_uploaded_file(request.FILES['file'])
            return render(request, 'importer/index.html')
    else:
        form = ImportForm()

    context = {'form': form}
    return render(request, 'importer/index.html', context)

