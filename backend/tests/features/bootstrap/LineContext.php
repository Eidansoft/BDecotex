<?php
require_once (dirname(__FILE__).'/CommonContextFunctions.php');
require_once (dirname(__FILE__).'/../../httpCallsAPI.php');

use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the Line context.
 */
class LineContext extends CommonContextFunctions implements Context, SnippetAcceptingContext
{
    protected $url;
    
    public function __construct()
    {
        $this->url = "http://".BDECOTEX_SERVER.BDECOTEX_MAIN_URL."/line";
    }

    /**
     * @When el usuario crea la linea :arg1 con codigo :arg2
     */
    public function elUsuarioCreaLaLineaConCodigo($arg1, $arg2)
    {
        $method = UrlApi::URL_METHOD_POST;
        $url = $this->url;
        $lineData = ["name"  => ("null" == $arg1 ? "" : $arg1),
                       "code"         => ("null" == $arg2 ? "" : $arg2)];
        $this->callUrl($method, $url, $lineData);
    }

    /**
     * @When el usuario modifica la linea al nuevo nombre :arg1 con codigo :arg2
     */
    public function elUsuarioModificaLaLineaAlNuevoNombreConCodigo($arg1, $arg2)
    {
        $lineaPreviamenteCreada = $this->responseJson;
        $method = UrlApi::URL_METHOD_PUT;
        $url = $this->url . "/" . $lineaPreviamenteCreada->id_line;
        $lineData = ["name"  => ("null" == $arg1 ? "" : $arg1),
                     "code"         => ("null" == $arg2 ? "" : $arg2)];
        $this->callUrl($method, $url, $lineData);
    }

    /**
     * @When el usuario elimina la linea creada
     */
    public function elUsuarioEliminaLaLineaCreada()
    {
        $lineaPreviamenteCreada = $this->responseJson;
        $method = UrlApi::URL_METHOD_DELETE;
        $url = $this->url . "/" . $lineaPreviamenteCreada->id_line;
        $this->callUrl($method, $url);
    }

    /**
     * @Given que en el sistema existen las lineas:
     */
    public function queEnElSistemaExistenLasLineas(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row) {
            $this->elUsuarioCreaLaLineaConCodigo($row['NOMBRE'], $row['CODIGO']);
        }
    }

    /**
     * @When el usuario solicita el listado de todas las lineas
     */
    public function elUsuarioSolicitaElListadoDeTodasLasLineas()
    {
        $method = UrlApi::URL_METHOD_GET;
        $url = $this->url;
        $this->callUrl($method, $url);
    }

    /**
     * @Then el sistema incluye el listado con las lineas:
     */
    public function elSistemaIncluyeElListadoConLasLineas(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row) {
            if ( ! $this->findLineIntoJsonResponse($row['NOMBRE'], $row['CODIGO']) ){
                throw new Exception("Expected line '" . $row['NOMBRE'] . "' with code '" . $row['CODIGO'] . "' not found at server response");
            }
        }
    }
    
    public function findLineIntoJsonResponse($name, $code = null) {
        foreach ($this->responseJson as $line) {
            if ($line->name == $name){
                if ($code == null || $line->code == $code){
                    return $line->id_line;
                }
            }
        }
        return FALSE;
    }
}
