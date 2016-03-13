<?php

/**
 * Description of BDecotexImporter
 *
 * @author alex
 */
abstract class BDecotexImporter {
    
    protected $xmlContent;
    protected $dao;

    public function __construct($xmlFilePath, $dao) {
        $this->dao = $dao;
        $fh = fopen($xmlFilePath, 'r');
        while ($line = fgets($fh)) {
            $this->xmlContent .= $line;
        }
        fclose($fh);
    }
    
    public function truncateTable() {
        $this->dao->deleteAll();
    }

    public function processImport() {
        $objects = new SimpleXMLElement($this->xmlContent);
        foreach ($objects as $object) {
            $this->processObject($object);
        }
    }
    
    abstract protected function processObject($object);
}
