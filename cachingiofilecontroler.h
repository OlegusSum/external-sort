/*
 * Copyright 2017 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#ifndef CACHINGIOFILECONTROLER_H
#define CACHINGIOFILECONTROLER_H

#include<fstream>
#include<iostream>
#include<string>
#include<stdio.h>      
#include<stdlib.h>
#include<stdint.h>

using namespace std;


//RAII object to cache file operations
class cachingIOFileControler
{
private:
    cachingIOFileControler();
    cachingIOFileControler(const cachingIOFileControler &other);
    cachingIOFileControler& operator=(const cachingIOFileControler &other);
    fstream _caching_stream;
    unsigned long _cache_size; //in bytes
    uint8_t *_cache_buf;
    unsigned long _cache_pos;
    bool _is_modified;
    bool _is_last_block_cached;
    void _flush();
    void _get_next_block();
    unsigned long _cache_end_pos;
    bool _is_cache_initialized;
protected:
    const ios_base::openmode _flags;
    unsigned long long _file_pos; //start pos of current block in file1
public:
    cachingIOFileControler(const string &file_name, const ios_base::openmode &flags, const unsigned long cache_mem_size);
    ~cachingIOFileControler();
    uint8_t get_next(); //get value from cur file position
    void put(uint8_t); //put value to cur file position
    unsigned long long size();
    bool is_file_ended();
};

#endif // CACHINGIOFILECONTROLER_H
