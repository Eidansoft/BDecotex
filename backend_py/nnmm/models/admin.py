# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.contrib import admin
from .models import Sex, Line, Family, Model

# Register your models here.
admin.site.register(Sex)
admin.site.register(Line)
admin.site.register(Family)

class ModelAdministration(admin.ModelAdmin):
    fieldsets = [
        ('Type', {'fields': ['family', 'line', 'sex']}),
        ('Data', {'fields': ['description', 'notes']}),
        ('Properties', {'fields': ['front', 'back', 'neck', 'arm', 'client'], 'classes': ['collapse']}),
        ('Relations', {'fields': ['parent', 'old_code_parent'], 'classes': ['collapse']}),
    ]
    
    list_display = ('model_code', 'description')
    list_filter = ['sex', 'family', 'line']
    search_fields = ['model_code', 'description', 'notes']

    def save_model(self, request, obj, form, change):
        import ipdb; ipdb.set_trace()
        # To add a new model, we need to calculate the new variant
        if form.is_valid() and (
                (not change) or
                (change and (
                    'family' in form.changed_data or
                    'line' in form.changed_data or
                    'sex' in form.changed_data)
                )
        ):
            family = form.cleaned_data['family']
            line = form.cleaned_data['line']
            sex = form.cleaned_data['sex']
            
            obj.variant = Model.generate_next_free_variant(
                family, line, sex
            )

            # And also generate the model_code
            obj.model_code = '{}{}{}{}'.format(
                family.code, line.code,
                sex.code, obj.variant
            )

        super(ModelAdministration, self).save_model(request, obj, form, change)

admin.site.register(Model, ModelAdministration)
