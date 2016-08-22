<?php
require_once (dirname(__FILE__).'/CommonContextFunctions.php');
require_once (dirname(__FILE__).'/../../httpCallsAPI.php');

use Behat\Behat\Tester\Exception\PendingException;
use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the Family context.
 */
class FamilyContext extends CommonContextFunctions implements Context, SnippetAcceptingContext
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
     * @When el usuario crea la familia :arg1 con codigo :arg2
     */
    public function elUsuarioCreaLaFamiliaConCodigo($arg1, $arg2)
    {
        $method = UrlApi::URL_METHOD_POST;
        $url = "http://localhost/bdecotex/family";
        $familyData = ["description"  => ("null" == $arg1 ? "" : $arg1),
                       "code"         => ("null" == $arg2 ? "" : $arg2)];
        $this->callUrl($method, $url, $familyData);
    }

    /**
     * @When el usuario modifica la familia al nuevo nombre :arg1 con codigo :arg2
     */
    public function elUsuarioModificaLaFamiliaAlNuevoNombreConCodigo($arg1, $arg2)
    {
        $familiaPreviamenteCreada = $this->responseJson;
        $method = UrlApi::URL_METHOD_PUT;
        $url = "http://localhost/bdecotex/family/" . $familiaPreviamenteCreada->id_family;
        $familyData = ["description"  => ("null" == $arg1 ? "" : $arg1),
                       "code"         => ("null" == $arg2 ? "" : $arg2)];
        $this->callUrl($method, $url, $familyData);
    }

    /**
     * @When el usuario elimina la familia creada
     */
    public function elUsuarioEliminaLaFamiliaCreada()
    {
        $familiaPreviamenteCreada = $this->responseJson;
        $method = UrlApi::URL_METHOD_DELETE;
        $url = "http://localhost/bdecotex/family/" . $familiaPreviamenteCreada->id_family;
        $this->callUrl($method, $url);
    }

    /**
     * @Given que en el sistema existen las familias:
     */
    public function queEnElSistemaExistenLasFamilias(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row) {
            $this->elUsuarioCreaLaFamiliaConCodigo($row['NOMBRE'], $row['CODIGO']);
        }
    }

    /**
     * @When el usuario solicita el listado de todas las familias
     */
    public function elUsuarioSolicitaElListadoDeTodasLasFamilias()
    {
        $method = UrlApi::URL_METHOD_GET;
        $url = "http://localhost/bdecotex/family";
        $this->callUrl($method, $url);
    }

    /**
     * @Then el sistema incluye el listado con las familias:
     */
    public function elSistemaIncluyeElListadoConLasFamilias(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row) {
            if ( ! $this->findFamilyIntoJsonResponse($row['NOMBRE'], $row['CODIGO']) ){
                throw new Exception("Expected family '" . $row['NOMBRE'] . "' with code '" . $row['CODIGO'] . "' not found at server response");
            }
        }
    }
    
    public function findFamilyIntoJsonResponse($name, $code = null) {
        foreach ($this->responseJson as $family) {
            if ($family->description == $name){
                if ($code == null || $family->code == $code){
                    return $family->id_family;
                }
            }
        }
        return FALSE;
    }
}
