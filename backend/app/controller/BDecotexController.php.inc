<?php

class BDecotexController {
    
    protected $dao;
    
    public function __construct($dao) {
        $this->dao = $dao;
    }

    function getById($id) {
        $obj = $this->dao->getById($id);
        if ($obj == NULL){
            throw new BDecotexException(4, 404, "There is no ".$this->dao->getTable_name()." identified with ID $id");
        }
        return $obj;
    }
    
    function getAll(){
        return $this->dao->getAll();
    }
    
    function delete($id) {
        // Check the $object with ID exists, if not it will raise exception
        $this->getById($id);
        
        $res = $this->dao->delete($id);
        if (!$res) {
            throw new BDecotexException(5, 500, "Error deleting the ".$this->dao->getTable_name()." with ID: '$id'");
        }
    }
}

?>