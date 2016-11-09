<?php
require_once (dirname(__FILE__).'/BDecotexDAOImpl.php.inc');

class SexDAOImpl extends BDecotexDAOImpl {
    
    public function __construct() {
        parent::__construct('sex');
    }
    
    public function create(SexDTO $sex) {
        return $this->getModifiedIdExecutingQuery("INSERT INTO $this->table_name ("
                                                    . "name, "
                                                    . "code"
                                                 . ") VALUES ("
                                                    . "'" . $sex->getName() . "', "
                                                    . "'" . $sex->getCode() . "'"
                                                 . ")");
    }

    public function update($id, SexDTO $sex) {
        return $this->executeQuery("UPDATE $this->table_name "
                                 . "SET name = '" . $sex->getName() . "', "
                                 . "code = '" . $sex->getCode() . "' "
                                 . "WHERE id_$this->table_name = $id");
    }
    
    public function getByCode($sexCode) {
        $sex = $this->getSingleResult("SELECT * FROM $this->table_name WHERE code = '$sexCode'");
        return $sex;
    }
}
?>