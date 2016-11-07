<?php
require_once (dirname(__FILE__).'/ControllerException.php.inc');

class BDecotexController {
    
    protected $dao;
    
    public function __construct($dao) {
        $this->dao = $dao;
    }

    function getById($id) {
        try{
            return $this->dao->getById($id);
        } catch (DAOException $e) {
            throw new ControllerException($e->code, $e->httpCode, $e->message);
        }
    }
    
    function getAll(){
        return $this->dao->getAll();
    }
    
    function delete($id) {
        // Check the $object with ID exists, if not it will raise exception
        $this->getById($id);
        
        $res = $this->dao->delete($id);
        if (!$res) {
            throw new ControllerException(5, 500, "Error deleting the ".$this->dao->getTable_name()." with ID: '$id'");
        }
    }
}

?>