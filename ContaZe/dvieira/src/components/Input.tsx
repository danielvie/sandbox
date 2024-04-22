import React from 'react'
import { Form, InputGroup } from "react-bootstrap";

export default function Input() {
    
    return (
        <Form>
            <InputGroup>
                <InputGroup.Prepend>
                  <InputGroup.Text id="inputGroupPrepend">@</InputGroup.Text>
                </InputGroup.Prepend>
                <Form.Control
                  type="text"
                  placeholder="Username"
                  aria-describedby="inputGroupPrepend"
                  name="username"
                //   value={values.username}
                //   onChange={handleChange}
                //   isInvalid={!!errors.username}
                />
                <Form.Control.Feedback type="invalid">
                  {/* {errors.username} */}
                </Form.Control.Feedback>
              </InputGroup>
        </Form>
    )
}
