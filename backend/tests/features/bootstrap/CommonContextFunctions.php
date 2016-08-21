<?php
require_once (dirname(__FILE__).'/CommonAssertions.php');
require_once (dirname(__FILE__).'/../../httpCallsAPI.php');
require_once (dirname(__FILE__).'/../../../app/model/BDecotexDAOImpl.php.inc');

use Behat\Behat\Tester\Exception\PendingException;
use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the specific context.
 */
class CommonContextFunctions extends CommonAssertions implements Context, SnippetAcceptingContext
{
    protected $responseJson;
    protected $responseCode;

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
     * @Given que la tabla :arg1 esta vacia
     */
    public function queLaTablaEstaVacia($arg1)
    {
        $dao = new BDecotexDAOImpl($arg1);
        $dao->deleteAll();
    }

    /**
     * @Then el sistema devuelve un codigo http :arg1
     */
    public function elSistemaDevuelveUnCodigoHttp($arg1)
    {
        $this->assertSame(
            intval($arg1),
            $this->responseCode,
            "The system returned HTTP code " . $this->responseCode . ", instead $arg1"
        );
    }
    
    /**
     * @Then el sistema incluye en la respuesta los siguientes atributos:
     */
    public function elSistemaIncluyeEnLaRespuestaLosSiguientesAtributos(TableNode $table)
    {
        $hash = $table->getHash();
        foreach ($hash as $row) {
            if ( ! array_key_exists($row['ATRIBUTO'], $this->responseJson)){
                throw new Exception("Missing mandatory atribute '" . $row['ATRIBUTO'] . "'");
            }
            if (array_key_exists("VALOR", $row) && $row['VALOR'] != ""){
                if (1 == preg_match("/^regex\((.+)\)$/", $row['VALOR'], $coincidencias)){
                    $this->assertStringMatchesFormat(
                    $coincidencias[1],
                    $this->responseJson->id_family,
                    "Expected value for '" . $row['ATRIBUTO'] . "' attribute was the regex expression '" . $coincidencias[1] . "', but the value '" . $this->responseJson->$row['ATRIBUTO'] . "' found at the response did not match the expression"
                );
                } else {
                    $this->assertSame(
                        $row['VALOR'],
                        $this->responseJson->$row['ATRIBUTO'],
                        "Expected value for '" . $row['ATRIBUTO'] . "' attribute was '" . $row['VALOR'] . "', but '" . $this->responseJson->$row['ATRIBUTO'] . "' was found"
                    );
                }
            }
        }
    }

    protected function callUrl($method, $url, $params = null) {
        if (null == $params){
            $conection = new UrlApi($url, $method);
        } else {
            $conection = new UrlApi($url, $method, json_encode($params));
        }
        $conection->call();
        $this->responseCode = $conection->getHttpCode();
        $this->responseJson = json_decode($conection->getResponse());
    }
}
