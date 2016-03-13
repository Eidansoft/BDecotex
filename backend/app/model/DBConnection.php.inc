<?php
require_once "../config.php.inc";
require_once (dirname(__FILE__).'/BDecotexException.php.inc');

class DBConnection 
{ 
    protected $_db; 

    public function __construct() 
    { 
        $this->_db = new mysqli(DB_HOST, DB_USER, DB_PASS, DB_NAME); 

        if ( $this->_db->connect_errno ) 
        { 
            throw new BDecotexException(1, 500);
        } 

        $this->_db->set_charset(DB_CHARSET); 
    }
    
    protected function get_db() {
        return $this->_db;
    }
    
    protected function getListResults($sql){
        $query = $this->get_db()->query($sql);
        if (!$query) {
            throw new BDecotexException(2, 500, "Error executing SQL to get a list of elements: $sql");
        }
        
        while ($row = $query->fetch_assoc()) {
            $list[] = $row;
        }
        return $list;
    }
    
    protected function getSingleResult($sql){
        $executableQuery = $sql . " LIMIT 1";
        $query = $this->get_db()->query($executableQuery);
        if (!$query) {
            throw new BDecotexException(2, 500, "Error executing SQL to get a single element: $executableQuery");
        }
        return $query->fetch_array(MYSQLI_ASSOC);
    }
    
    protected function executeQuery($sql){
        $query = $this->get_db()->query($sql);
        if (!$query) {
            throw new BDecotexException(2, 500, "Error executing SQL query: $sql");
        }
        return $query;
    }
    
    protected function getModifiedIdExecutingQuery($sql) {
        $this->executeQuery($sql);
        return $this->get_db()->insert_id;
    }
} 
?>
