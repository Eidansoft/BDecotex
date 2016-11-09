<?php
require_once (dirname(__FILE__).'/BDecotexDTO.php.inc');
/**
 * Description of SexDTO
 *
 * @author alex
 */
class SexDTO extends BDecotexDTO {
    private $id_sex;
    private $name;
    private $code;
    
    function __construct($modelArray) {
        $sanitizeRules = array(
            'id_sex'                => array('filter'    => FILTER_VALIDATE_INT,
                                             'options'   => array('min_range' => 0, 'max_range' => 2147483648)),
            'name'                  => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH),
            'code'                  => array('filter'    => FILTER_SANITIZE_SPECIAL_CHARS,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_ENCODE_HIGH),
            );
        
        $sanitationAndValidationRules = [
            BDecotexDTO::SANITIZE_RULE_NAME => $sanitizeRules,
            'required'       => [['name'], ['code']],
            'integer'        => [['id_sex']],
            'lengthMin'      => [['name', 4], ['code', 1]],
            'lengthMax'      => [['name', 50], ['code', 50]]
            ];
        parent::__construct($modelArray, $sanitationAndValidationRules);
        
    }
    
    protected function buildDto($modelArray) {
        
        if (isset($modelArray['id_sex'])){
            $this->id_sex = $modelArray['id_sex'];
        }
        
        $this->name = $modelArray['name'];
        $this->code = $modelArray['code'];
    }
    
    function getId_sex() {
        return $this->id_sex;
    }

    function getName() {
        return $this->name;
    }

    function getCode() {
        return $this->code;
    }


}
