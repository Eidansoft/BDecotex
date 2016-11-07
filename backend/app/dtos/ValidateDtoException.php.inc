<?php
require_once (dirname(__FILE__)."/../view/ViewException.php.inc");
/**
 * Description of ValidateDtoException
 *
 * @author alex
 */
class ValidateDtoException extends ViewException {
    //put your code here
    public function __construct($code, $httpCode = 500, $otherInfo = null) {
        parent::__construct($code, $httpCode, $otherInfo);
    }
}

?>