<?php
require_once (dirname(__FILE__).'/BDecotexDAOImpl.php.inc');

class LineDAOImpl extends BDecotexDAOImpl {
    
    public function __construct() {
        parent::__construct('line');
    }
    
    public function create($name) {
        return $this->getModifiedIdExecutingQuery("INSERT INTO $this->table_name ("
                                                    . "name "
                                                 . ") VALUES ("
                                                    . "'$name' "
                                                 . ")");
    }

    public function update($id, $name) {
        return $this->executeQuery("UPDATE $this->table_name "
                                 . "SET name = '$name, "
                                 . "WHERE id_$this->table_name = $id");
    }
}
?>