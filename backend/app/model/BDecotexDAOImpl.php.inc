<?php
require_once (dirname(__FILE__).'/DBConnection.php.inc');

class BDecotexDAOImpl extends DBConnection {
    
    protected $table_name;
    
    public function __construct($table_name) {
        parent::__construct();
        $this->table_name = $table_name;
    }

    public function delete($id) {
        return $this->executeQuery("DELETE FROM $this->table_name WHERE id_$this->table_name = $id");
    }

    public function deleteAll() {
        return $this->executeQuery("TRUNCATE $this->table_name");
    }
    
    public function getAll() {
        $families = $this->getListResults("SELECT * FROM $this->table_name");
        return $families;
    }

    public function getById($id) {
        $family = $this->getSingleResult("SELECT * FROM $this->table_name WHERE id_$this->table_name = $id");
        return $family;
    }
    
    public function getTable_name() {
        return $this->table_name;
    }
}