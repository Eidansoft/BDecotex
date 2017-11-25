# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models


class Sex(models.Model):
    code = models.CharField(max_length=2, unique=True)
    name = models.CharField(max_length=50)

    def __unicode__(self):
        return self.name

    def __str__(self):
        return self.name


class Line(models.Model):
    code = models.CharField(max_length=2, unique=True)
    name = models.CharField(max_length=50)

    def __unicode__(self):
        return self.name

    def __str__(self):
        return self.name

class Family(models.Model):
    code = models.CharField(max_length=2, unique=True)
    name = models.CharField(max_length=50)

    def __unicode__(self):
        return self.name

    def __str__(self):
        return self.name

class Modelo(models.Model):
    sex = models.ForeignKey(Sex, on_delete=models.PROTECT)
    line = models.ForeignKey(Line, on_delete=models.PROTECT)
    family = models.ForeignKey(Family, on_delete=models.PROTECT)
    # Variant is a automatically caltulated value
    variant = models.PositiveSmallIntegerField()
    # model_code is calculated field, but I store it because
    # we need to index it in order to search for it
    model_code = models.CharField(max_length=10)

    description = models.CharField(max_length=100)
    front = models.CharField(max_length=100, null= True, blank=True, default='')
    back = models.CharField(max_length=100, null= True, blank=True, default='')
    neck = models.CharField(max_length=100, null= True, blank=True, default='')
    arm = models.CharField(max_length=100, null= True, blank=True, default='')
    notes = models.TextField(max_length=3000, null= True, blank=True, default='')
    client = models.CharField(max_length=100, null= True, blank=True, default='')
    parent = models.ForeignKey('self', on_delete=models.PROTECT, null= True, blank=True, default='')
    old_code_parent = models.CharField(max_length=10, null= True, blank=True, default='')

    def __unicode__(self):
        return self.model_code

    def __str__(self):
        return self.model_code

    def save(self, *args, **kwargs):
        '''I override the save method in order to
        calculate properly the model_code, because
        model_code is a calculated field but I need
        store it in order to index it at DB and search
        for it'''
        self.model_code = '{}{}{}{}'.format(
                self.family.code, self.line.code,
                self.sex.code, self.variant
            )
        super(Modelo, self).save(*args, **kwargs)

    @staticmethod
    def generate_next_free_variant(family, line, sex):
        '''
        This method calculate the next free variant for a given
        family, line and sex
        '''
        res = 0

        models = Modelo.objects.filter(family=family, line=line, sex=sex)
        if models:
            already_existent_variants = [
                model.variant for model in models
            ]
            res = [
                n
                for n in range(len(already_existent_variants)+1)
                if n not in already_existent_variants
            ][0]
        
        return res
