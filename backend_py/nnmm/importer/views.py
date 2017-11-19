# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render

# Create your views here.
from forms import ImportForm
from MdbAccessReader import MdbAccessReader
# from nnmm.models.models import Family


def mdbimport(request):

    context = {}
    if request.method == 'POST':
        form = ImportForm(request.POST, request.FILES)
        if form.is_valid():
            import ipdb; ipdb.set_trace(context=21)
            handle_uploaded_file(request.FILES['file'])
            return render(request, 'importer/index.html')
        else:
            context['error'] = 'Datos no validos'

    form = ImportForm()
    context['form'] = form
    return render(request, 'importer/index.html', context)

def handle_uploaded_file(f):
    temp_file = 'dbimport.mdb'
    with open(temp_file, 'wb+') as destination:
        for chunk in f.chunks():
            destination.write(chunk)
    import ipdb; ipdb.set_trace(context=21)

    families = MdbAccessReader.get_content_table_dict(temp_file, 'Familias')
    save_families(families)
    
    # lines = MdbAccessReader.get_content_table_dict(temp_file, 'Lineas')
    # save_lines(lines)
    
    # sexs = MdbAccessReader.get_content_table_dict(temp_file, 'Sexo')
    # save_sex(sexs)
    
    # models = MdbAccessReader.get_content_table_dict(temp_file, 'Nuevos_Modelos')
    # save_models(models)

def save_families(families):
    for fam in families:
        # f= Family.objects.create(code=fam.get('Cod'),
                              # name=fam.get('Desc'))
        # f.save()
        pass



