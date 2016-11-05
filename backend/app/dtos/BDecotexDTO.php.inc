<?php
require_once (dirname(__FILE__).'/../libs/valitron/Validator.php');
require_once (dirname(__FILE__).'/ValidateDtoException.php.inc');

/**
 * Description of BDecotexDTO
 *
 * @author alex
 */
abstract class BDecotexDTO {
    const SANITIZE_RULE_NAME = 'sanitize';
    protected $validator;
    
    function __construct($paramsArray, $sanitationAndValidationRules) {
        if (array_key_exists(BDecotexDTO::SANITIZE_RULE_NAME, $sanitationAndValidationRules)) {
            $this->sanitizeText($paramsArray, $sanitationAndValidationRules[BDecotexDTO::SANITIZE_RULE_NAME]);
            // Remove the sanitization rules to do not disturb validation api
            unset($sanitationAndValidationRules[BDecotexDTO::SANITIZE_RULE_NAME]);
        }
        $this->validate($paramsArray, $sanitationAndValidationRules);
    }
    
    private function validate($paramsArray, $validationRulesArray) {
        Valitron\Validator::langDir(dirname(__FILE__).'/../libs/valitron/');
        Valitron\Validator::lang('es');
        
        $this->validator = new Valitron\Validator($paramsArray);
        $this->validator->rules($validationRulesArray);
        if ($this->validator->validate()) {
            $this->buildDto($paramsArray);
        } else {
            $message = "Error/s found: [";
            foreach($this->validator->errors() as $attributeErrors) {
                foreach($attributeErrors as $errorDescription) {
                    $message .= $errorDescription . ", ";
                }
            }
            $message = substr($message, 0, strlen($message)-2) . "]";
            throw new ValidateDtoException(4, 400, $message);
        }
    }
    
    private function sanitizeText(&$paramsArray, $sanitizeRules) {
        $paramsArray = filter_var_array($paramsArray, $sanitizeRules);
    }
    
    protected abstract function buildDto($array);
}

?>