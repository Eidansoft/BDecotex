<?php
require_once (dirname(__FILE__).'/BDecotexDAOImpl.php.inc');

class ModelDAOImpl extends BDecotexDAOImpl {
    
    public function __construct() {
        parent::__construct('model');
    }
    
    public function create($familyId, $lineId, $sexId, $variant,
            $description = 'NULL', $front = 'NULL', $back = 'NULL', 
            $neck = 'NULL', $arm = 'NULL', $observations = 'NULL',
            $client = 'NULL', $idParent = 'NULL',
            $oldRef = 'NULL', $modelNumberParent = 'NULL') {
        
        $datetime1 = new DateTime();
        
        // I check that there is no empty string, I prefer to store null
        $description = ($description == '' ? "NULL" : "'$description'");
        $front = ($front == '' ? "NULL" : "'$front'");
        $back = ($back == '' ? "NULL" : "'$back'");
        $neck = ($neck == '' ? "NULL" : "'$neck'");
        $arm = ($arm == '' ? "NULL" : "'$arm'");
        $observations = ($observations == '' ? "NULL" : "'$observations'");
        $client = ($client == '' ? "NULL" : "'$client'");
        $idParent = ($idParent == '' ? NULL : "$idParent");
        $oldRef = ($oldRef == '' ? "NULL" : "'$oldRef'");
        $modelNumberParent = ($modelNumberParent == '' ? "NULL" : "'$modelNumberParent'");
        
        return $this->getModifiedIdExecutingQuery("INSERT INTO $this->table_name ("
                                                    . "xid_family, "
                                                    . "xid_line, "
                                                    . "xid_sex, "
                                                    . "variant, "
                                                    . "description, "
                                                    . "front, "
                                                    . "back, "
                                                    . "neck, "
                                                    . "arm, "
                                                    . "observations, "
                                                    . "model_number_parent, "
                                                    . "xid_model_parent, "
                                                    . "creation_date, "
                                                    . "client, "
                                                    . "old_ref "
                                                 . ") VALUES ("
                                                    . "$familyId, "
                                                    . "$lineId, "
                                                    . "$sexId, "
                                                    . "$variant, "
                                                    . "$description, "
                                                    . "$front, "
                                                    . "$back, "
                                                    . "$neck, "
                                                    . "$arm, "
                                                    . "$observations, "
                                                    . "$modelNumberParent, "
                                                    . "$idParent, "
                                                    . $datetime1->getTimestamp() . ", "
                                                    . "$client, "
                                                    . "$oldRef  "
                                                 . ")");
    }
    
    public function update($id, $field, $value) {
        return $this->executeQuery("UPDATE $this->table_name "
                                 . "SET $field = " . (is_string($value) ? "'$value'" : "$value" ) . " "
                                 . "WHERE id_$this->table_name = $id");
    }
    
    public function getByCode($family, $line, $sex, $variant) {
        return $this->getSingleResult("SELECT * "
                                    . "FROM $this->table_name "
                                    . "WHERE xid_family = $family "
                                    . "AND xid_line = $line "
                                    . "AND xid_sex = $sex "
                                    . "AND variant = $variant");
    }
}
?>