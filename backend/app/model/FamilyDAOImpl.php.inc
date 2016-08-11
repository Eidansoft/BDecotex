<?php
require_once (dirname(__FILE__).'/BDecotexDAOImpl.php.inc');

class FamilyDAOImpl extends BDecotexDAOImpl {
    
    public function __construct() {
        parent::__construct('family');
    }
    
    public function create($description, $code) {
        return $this->getModifiedIdExecutingQuery("INSERT INTO $this->table_name ("
                                                    . "description, "
                                                    . "code"
                                                 . ") VALUES ("
                                                    . "'$description', "
                                                    . "'$code'"
                                                 . ")");
    }

    public function update($id, $description, $code) {
        return $this->executeQuery("UPDATE $this->table_name "
                                 . "SET description = '$description', "
                                 . " code = '$code'"
                                 . "WHERE id_$this->table_name = $id");
    }
    
    public function getByCode($familyCode) {
        $family = $this->getSingleResult("SELECT * FROM $this->table_name WHERE code = '$familyCode'");
        return $family;
    }
}
?>