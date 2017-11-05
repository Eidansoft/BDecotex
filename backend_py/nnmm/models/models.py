# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models


class Sex(models.Model):
    code = models.CharField(max_length=2, unique=True)
    name = models.CharField(max_length=50)

    def __str__(self):
        return self.name


class Model(models.Model):
    sex = models.ForeignKey(Sex, on_delete=models.CASCADE)
    description = models.CharField(max_length=200)

    def __str__(self):
        return self.description

