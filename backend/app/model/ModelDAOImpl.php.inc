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
                                                    . "'$description', "
                                                    . "'$front', "
                                                    . "'$back', "
                                                    . "'$neck', "
                                                    . "'$arm', "
                                                    . "'$observations', "
                                                    . "'$modelNumberParent', "
                                                    . ($idParent == '' ? 'NULL' : $idParent) . ", "
                                                    . $datetime1->getTimestamp() . ", "
                                                    . "'$client', "
                                                    . "'$oldRef'  "
                                                 . ")");
    }

//    public function create2($id_model, $familyId, $lineId, $sexId, $variant,
//            $description, $front, $back, $neck, $arm, $observations,
//            $oldModelNumber, $parentModelId) {
//        $datetime1 = new DateTime();
//        return $this->getModifiedIdExecutingQuery("INSERT INTO model2 ("
//                                                    . "id_model, "
//                                                    . "xid_family, "
//                                                    . "xid_line, "
//                                                    . "xid_sex, "
//                                                    . "variant, "
//                                                    . "description, "
//                                                    . "front, "
//                                                    . "back, "
//                                                    . "neck, "
//                                                    . "arm, "
//                                                    . "observations, "
//                                                    . "old_model_number, "
//                                                    . "xid_model_parent, "
//                                                    . "creation_date "
//                                                 . ") VALUES ("
//                                                    . "'$id_model', "
//                                                    . "'$familyId', "
//                                                    . "'$lineId', "
//                                                    . "'$sexId', "
//                                                    . "'$variant', "
//                                                    . "'$description', "
//                                                    . "'$front', "
//                                                    . "'$back', "
//                                                    . "'$neck', "
//                                                    . "'$arm', "
//                                                    . "'$observations', "
//                                                    . "'$oldModelNumber', "
//                                                    . "'$parentModelId', "
//                                                    . "'" . $datetime1->getTimestamp() . "'"
//                                                 . ")");
//    }
    
    public function update($id, $description) {
        return $this->executeQuery("UPDATE $this->table_name "
                                 . "SET description = '$description' "
                                 . "WHERE id_$this->table_name = $id");
    }
}
?>