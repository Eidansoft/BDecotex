<?php
require_once (dirname(__FILE__)."/../view/IJSonable.php.inc");
require_once (dirname(__FILE__)."/../view/JSonable.php.inc");

class BDecotexException extends Exception implements IJSonable {
    
    public $code;
    public $message;
    public $httpCode;

    public function __construct($code, $httpCode = 500, $otherInfo = null) {
        $this->code = $code;
        $this->httpCode = $httpCode;
        $this->message = $otherInfo;
        parent::__construct($otherInfo, $code, null);
    }

    public function getJsonData() {
        $jsonizer = new JSonable();
        return $jsonizer->getJsonData($this);
    }
    
    public function getHttpError(){
        switch ($this->httpCode) {
            case 400:
                $httpMsg = ' 400 Bad Request';
                break;
            case 403:
                $httpMsg = ' 403 Forbidden';
                break;
            case 404:
                $httpMsg = ' 404 Not Found';
                break;
            case 500:
            default :
                $httpMsg = ' 500 Internal Server Error';
        }
        return $httpMsg;
    }
    
    public function throwToClient(){
        header($_SERVER['SERVER_PROTOCOL'] . $this->getHttpError(), true, $this->httpCode);
        header("Content-Type: application/json");
        echo json_encode($this->getJsonData());
        die();
    }
}
?>