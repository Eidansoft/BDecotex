# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render

# Create your views here.
from forms import ImportForm
from MdbAccessReader import MdbAccessReader
from modelo.models import Family, Line, Sex, Modelo


def mdbimport(request):

    context = {}
    if request.method == 'POST':
        form = ImportForm(request.POST, request.FILES)
        if form.is_valid():
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

    families = MdbAccessReader.get_content_table_dict(temp_file, 'Familias')
    save_families(families)
    
    lines = MdbAccessReader.get_content_table_dict(temp_file, 'Lineas')
    save_lines(lines)
    
    sexs = MdbAccessReader.get_content_table_dict(temp_file, 'Sexo')
    save_sex(sexs)
    
    models = MdbAccessReader.get_content_table_dict(temp_file, 'Nuevos_Modelos')
    save_models(models)

def save_families(families):
    for fam in families:
        f= Family.objects.create(code=fam.get('Cod'),
                              name=fam.get('Desc'))
        f.save()

def save_lines(lines):
    for lin in lines:
        l= Line.objects.create(code=lin.get(u'Línea'),
                              name=lin.get(u'Descripción'))
        l.save()

def save_sex(sexs):
    for sex in sexs:
        s = Sex.objects.create(code=sex.get(u'Código'),
                              name=sex.get(u'Sexo'))
        s.save()


def save_models(lista_modelos):
    import ipdb; ipdb.set_trace(context=21)
    for modelo in lista_modelos:
        m = Modelo.objects.create(code=modelo.get(u'Línea'),
                              name=modelo.get(u'Descripción'))
        m.save()



