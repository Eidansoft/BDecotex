<?php
/**
 * Simple PHP API to perform HTTP calls throught cURL
 * @author Alejandro Lorente 13/08/2016
 */

class UrlApi {

	const URL_METHOD_GET = 0;
	const URL_METHOD_POST = 1;
	const URL_METHOD_PUT = 2;
	const URL_METHOD_DELETE = 3;

	private $url;
	private $method;
	private $params;
        
        private $requestInfo;
        private $responseAsString;

	/**
	 * The contructor needs the url, the method (use the defined constants) and params (in JSON string)
	 */
	public function __construct($url, $method = UrlApi::URL_METHOD_GET, $params = null) {
		$this->url = $url;
		$this->method = $method;
		$this->params = $params;
	}

	public function call(){
		// create connection object
		$ch = curl_init();
		// configure connection
		curl_setopt($ch, CURLOPT_URL, $this->url);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		if ($this->method != UrlApi::URL_METHOD_DELETE){
			curl_setopt($ch, CURLOPT_HEADER, true);
		}

		if ($this->method == UrlApi::URL_METHOD_POST || $this->method == UrlApi::URL_METHOD_PUT){
			curl_setopt($ch, CURLOPT_POST, true);
			curl_setopt($ch, CURLOPT_POSTFIELDS, $this->params);
			curl_setopt($ch, CURLOPT_HTTPHEADER, array(
				'Content-Type: application/json',
				'Content-Length: ' . strlen($this->params)
			));
		}

		if ($this->method == UrlApi::URL_METHOD_GET){
			curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "GET");
		} else if($this->method == UrlApi::URL_METHOD_POST){
			curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
		} else if($this->method == UrlApi::URL_METHOD_PUT){
			curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
		} else if($this->method == UrlApi::URL_METHOD_DELETE){
			curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "DELETE");
		}
                
		// execute the request
		$this->responseAsString = curl_exec($ch);
                $this->requestInfo = curl_getinfo($ch);
                
		// close connection
		curl_close($ch);
                
                return $this->responseAsString;
	}
        
        public function getHttpCode(){
            $this->checkRequestPerformed();
            return $this->requestInfo['http_code'];
        }
        
        public function getResponse(){
            $this->checkRequestPerformed();
            return substr($this->responseAsString, strlen($this->responseAsString) - $this->requestInfo['size_download']);
        }
        
        public function getContentType(){
            $this->checkRequestPerformed();
            return $this->requestInfo['content_type'];
        }
        
        private function checkRequestPerformed(){
            if ($this->requestInfo == null){
                throw new Exception("The request must be called first.");
            }
            return true;
        }
}
?>