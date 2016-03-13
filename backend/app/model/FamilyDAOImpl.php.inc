<?php
require_once (dirname(__FILE__).'/BDecotexDAOImpl.php.inc');

class FamilyDAOImpl extends BDecotexDAOImpl {
    
    public function __construct() {
        parent::__construct('family');
    }
    
    public function create($description) {
        return $this->executeQuery("INSERT INTO $this->table_name ("
                                    . "description"
                                 . ") VALUES ("
                                    . "'$description'"
                                 . ")");
    }

    public function update($id, $description) {
        return $this->executeQuery("UPDATE $this->table_name "
                                 . "SET description = '$description' "
                                 . "WHERE id_$this->table_name = $id");
    }
}
?>