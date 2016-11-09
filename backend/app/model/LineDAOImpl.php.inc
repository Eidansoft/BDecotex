<?php
require_once (dirname(__FILE__).'/BDecotexDAOImpl.php.inc');

class LineDAOImpl extends BDecotexDAOImpl {
    
    public function __construct() {
        parent::__construct('line');
    }
    
    public function create(LineDTO $line) {
        return $this->getModifiedIdExecutingQuery("INSERT INTO $this->table_name ("
                                                    . "name, "
                                                    . "code "
                                                 . ") VALUES ("
                                                    . "'" . $line->getName() . "', "
                                                    . "'" . $line->getCode() . "'"
                                                 . ")");
    }

    public function update($id, LineDTO $line) {
        return $this->executeQuery("UPDATE $this->table_name "
                                 . "SET name = '" . $line->getName() . "', code = '" . $line->getCode() . "' "
                                 . "WHERE id_$this->table_name = $id");
    }
    
    public function getByCode($lineCode) {
        $line = $this->getSingleResult("SELECT * FROM $this->table_name WHERE code = '$lineCode'");
        return $line;
    }
}
?>