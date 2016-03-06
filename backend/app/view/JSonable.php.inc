<?php
require_once "./IJSonable.php.inc";

class JSonable implements IJSonable{
    
    public function getJsonData($obj = null){
        if ($obj == null){
            $obj = $this;
        }
        $var = get_object_vars($obj);
        foreach($var as $value){
            if(is_object($value) && method_exists($value,'getJsonData')){
                $value = $value->getJsonData();
            }
        }
        return $var;
    }
}

?>