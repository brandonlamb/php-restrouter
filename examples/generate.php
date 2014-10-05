<?php

$file = 'routes2.yml';

$comments = [];
#for ($i = 0; $i < 90000; $i++) {
#for ($i = 0; $i < 5; $i++) {
#for ($i = 0; $i < 50; $i++) {
for ($i = 0; $i < 100; $i++) {
#for ($i = 0; $i < 200; $i++) {
#for ($i = 0; $i < 300; $i++) {
#for ($i = 0; $i < 400; $i++) {
#for ($i = 0; $i < 600; $i++) {
#for ($i = 0; $i < 800; $i++) {
#for ($i = 0; $i < 1000; $i++) {
#for ($i = 0; $i < 2000; $i++) {
    $text1 = substr('abcdefghijklmnopqrstuvwxyz', mt_rand(0, 25), 1) . substr(md5(time()), 1);

    $comments[] = <<<END
- url: "/users/{i:id}/{$text1}"
  controller: "Controller_{$i}"
  methods: [GET, POST]
  consumes: ["application/json", "application/xml"]
  produces: ["application/json", "application/xml"]

END;
}

file_put_contents($file, "---\n" . implode("\n", $comments) . "...");
