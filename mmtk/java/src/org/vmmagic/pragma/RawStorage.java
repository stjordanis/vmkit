/*
 *  This file is part of the Jikes RVM project (http://jikesrvm.org).
 *
 *  This file is licensed to You under the Common Public License (CPL);
 *  You may not use this file except in compliance with the License. You
 *  may obtain a copy of the License at
 *
 *      http://www.opensource.org/licenses/cpl1.0.php
 *
 *  See the COPYRIGHT.txt file distributed with this work for information
 *  regarding copyright ownership.
 */
package org.vmmagic.pragma;

import java.lang.annotation.Retention;
import java.lang.annotation.Target;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.ElementType;
import org.vmmagic.Pragma;

/**
 * When applied to class this annotation indicates that the data component
 * of this field consists of an intrisically managed chunk of raw memory of
 * the specified size. This is used as the basic building block for native
 * width types.
 *
 * To construct types larger than those possible with RawStorage, simply
 * construct an type with multiple (Unboxed) fields.
 */
@Retention(RetentionPolicy.RUNTIME)
@Target({ElementType.TYPE})
@Pragma
public @interface RawStorage {
  boolean lengthInWords();
  int length();
}