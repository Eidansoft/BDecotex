<?php
require_once (dirname(__FILE__)."/IJSonable.php.inc");
require_once (dirname(__FILE__)."/JSonable.php.inc");

class ViewException extends Exception implements IJSonable {
    
    //This attributes need to be public in order the JSONizer be able to read it and create the JSon properly
    public $code;
    public $message;
    public $httpCode;

    public function __construct($code, $httpCode = 500, $otherInfo = null) {
        $this->code = $code;
        $this->httpCode = $httpCode;
        $this->message = $otherInfo;
        parent::__construct($otherInfo, $code, null);
    }

    public function getHttpCode() {
        return $this->httpCode;
    }

    public function getJsonData() {
        $jsonizer = new JSonable;
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
            case 409:
                $httpMsg = ' 409 Conflict';
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