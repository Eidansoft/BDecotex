import sys, subprocess, unicodedata
from backports import csv
from io import StringIO
 

class MdbAccessReader:
    '''This class is to import data from an old *.mdb file.
       There is a dependency on mdbtools external library, 
       that dependency must be installed in the system.'''

    @staticmethod
    def get_tables(mdb_file):
        '''Return te list of all tables found into the *.mdb file.

           Keyword arguments:
           mdb_file -- the path to the mdb file.

           Returns:
           An array with all table names
        '''
        table_names = subprocess.Popen(["mdb-tables", "-1", mdb_file], 
                               stdout=subprocess.PIPE).communicate()[0]
        tables = table_names.decode('UTF-8').split('\n')
        if u'' in tables:
            del tables[tables.index(u'')]

        return tables

    @staticmethod
    def get_content_table(mdb_file, table_name):
        '''Return the content of a table in CSV format.

           Keyword arguments:
           mdb_file -- the path to the mdb file.
           table_name -- the name of the table to get content.
        '''
        contents = subprocess.Popen(["mdb-export", mdb_file, table_name],
                                    stdout=subprocess.PIPE).communicate()[0]

        return contents.decode('UTF-8')

    @staticmethod
    def get_content_table_dict(mdb_file, table_name):
        '''Return teh content of a table in a Dict

           Keyword arguments:
           mdb_file -- the path to the mdb file.
           table_name -- the name of the table to get content.

           Returns:
           An array of dictionaries'''
        csv_content = MdbAccessReader.get_content_table(mdb_file, table_name)

        res = []
        virtual_file = StringIO(csv_content)
        reader = csv.DictReader(virtual_file)
        for row in reader:
            res.append(row)

        return res
        
