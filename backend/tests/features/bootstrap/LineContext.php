<?php
require_once (dirname(__FILE__).'/CommonContextFunctions.php');
require_once (dirname(__FILE__).'/../../httpCallsAPI.php');

use Behat\Behat\Tester\Exception\PendingException;
use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the Line context.
 */
class LineContext extends CommonContextFunctions implements Context, SnippetAcceptingContext
{
    /**
     * Initializes context.
     *
     * Every scenario gets its own context instance.
     * You can also pass arbitrary arguments to the
     * context constructor through behat.yml.
     */
    public function __construct()
    {
    }

    /**
     * @When el usuario crea la linea :arg1 con codigo :arg2
     */
    public function elUsuarioCreaLaLineaConCodigo($arg1, $arg2)
    {
        $method = UrlApi::URL_METHOD_POST;
        $url = "http://localhost/bdecotex/line";
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
        $url = "http://localhost/bdecotex/line/" . $lineaPreviamenteCreada->id_line;
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
        $url = "http://localhost/bdecotex/line/" . $lineaPreviamenteCreada->id_line;
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
        $url = "http://localhost/bdecotex/line";
        $this->callUrl($method, $url);
    }

    /**
     * @Then el sistema incluye el listado con las lineas:
     */
    public function elSistemaIncluyeElListadoConLasLineas(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row) {
            if ( ! $this->findFamilyIntoJsonResponse($row['NOMBRE'], $row['CODIGO']) ){
                throw new Exception("Expected line '" . $row['NOMBRE'] . "' with code '" . $row['CODIGO'] . "' not found at server response");
            }
        }
    }
    
    public function findFamilyIntoJsonResponse($name, $code = null) {
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
