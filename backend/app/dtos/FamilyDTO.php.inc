<?php
require_once (dirname(__FILE__).'/BDecotexDTO.php.inc');
/**
 * Description of FamilyDTO
 *
 * @author alex
 */
class FamilyDTO extends BDecotexDTO {
    private $id_family;
    private $description;
    private $code;
    
    function __construct($modelArray) {
        $sanitizeRules = array(
            'id_family'             => array('filter'    => FILTER_VALIDATE_INT,
                                             'options'   => array('min_range' => 0, 'max_range' => 2147483648)),
            'description'           => array('filter'    => FILTER_UNSAFE_RAW,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_STRIP_BACKTICK),
            'code'                  => array('filter'    => FILTER_UNSAFE_RAW,
                                             'flags'     => FILTER_FLAG_STRIP_LOW | FILTER_FLAG_STRIP_BACKTICK),
            );
        
        $sanitationAndValidationRules = [
            BDecotexDTO::SANITIZE_RULE_NAME => $sanitizeRules,
            'required'       => [['description'], ['code']],
            'integer'        => [['id_family']],
            'lengthMin'      => [['description', 4], ['code', 1]],
            'lengthMax'      => [['description', 50], ['code', 50]]
            ];
        parent::__construct($modelArray, $sanitationAndValidationRules);
        
    }
    
    protected function buildDto($modelArray) {
        
        if (isset($modelArray['id_family'])){
            $this->id_family = $modelArray['id_family'];
        }
        
        $this->description = $modelArray['description'];
        $this->code = $modelArray['code'];
    }
    
    function getId_family() {
        return $this->id_family;
    }

    function getDescription() {
        return $this->description;
    }

    function getCode() {
        return $this->code;
    }


}
