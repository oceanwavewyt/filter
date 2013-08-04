<?php
$data = 'content='.file_get_contents('./data.txt');
$context_options = array (
        'http' => array (
            'method' => 'POST',
            'header'=> "Content-Type: application/x-www-form-urlencoded\r\n"
                . "Content-Length: " . strlen($data) . "\r\n",
            'content' => $data
            )
        );

echo file_get_contents('http://127.0.0.1:10000/search',false, stream_context_create($context_options));
