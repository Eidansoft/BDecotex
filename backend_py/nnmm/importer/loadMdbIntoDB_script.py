import MdbAccessReader
from nnmm.models.models import Line

DB_FILE = '../../../NNMM.mdb'

lines = MdbAccessReader.get_content_table_dict(DB_FILE, 'Linea')
Line.objects.create(lines)
