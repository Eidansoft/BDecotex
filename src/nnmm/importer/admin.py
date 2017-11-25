# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.contrib import admin
from .models import Mdb

# Register your models here.

class ImporterAdministration(admin.ModelAdmin):

    def has_add_permission(self, request):
        return False

admin.site.register(Mdb, ImporterAdministration)
