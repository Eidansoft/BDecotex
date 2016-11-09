<?php
require_once (dirname(__FILE__).'/BDecotexDTO.php.inc');
/**
 * Description of LineDTO
 *
 * @author alex
 */
class LineDTO extends BDecotexDTO {
    private $id_line;
    private $name;
    private $code;
    
    function __construct($modelArray) {
        $sanitizeRules = array(
            'id_line'              => array('filter'    => FILTER_VALIDATE_INT,
                                             'options'   => array('min_range' => 0, 'max_range' => 2147483648)),
            'name'                  => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH),
            'code'                  => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH),
            );
        
        $sanitationAndValidationRules = [
            BDecotexDTO::SANITIZE_RULE_NAME => $sanitizeRules,
            'required'       => [['name'], ['code']],
            'integer'        => [['id_line']],
            'lengthMin'      => [['name', 4], ['code', 1]],
            'lengthMax'      => [['name', 50], ['code', 50]]
            ];
        parent::__construct($modelArray, $sanitationAndValidationRules);
        
    }
    
    protected function buildDto($modelArray) {
        
        if (isset($modelArray['id_line'])){
            $this->id_line = $modelArray['id_line'];
        }
        
        $this->name = $modelArray['name'];
        $this->code = $modelArray['code'];
    }
    
    function getId_line() {
        return $this->id_line;
    }

    function getName() {
        return $this->name;
    }

    function getCode() {
        return $this->code;
    }


}
