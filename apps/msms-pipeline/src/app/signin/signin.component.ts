import { AccountService } from './../account.service';
import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup } from '@angular/forms';

@Component({
  selector: 'cprobid-signin',
  templateUrl: './signin.component.html',
  styleUrls: ['./signin.component.scss']
})
export class SigninComponent implements OnInit {
  signinForm = new FormGroup({
    email: new FormControl(''),
    password: new FormControl(''),
  });
  error: string;
  constructor(private account: AccountService) { }

  ngOnInit() {
  }

  onSubmit() {
    const {email, password} = this.signinForm.value;
    this.account.signin(email.trim(),password.trim()).toPromise().then(
      (res) => {}
    ).catch(
      (err) => {
        console.log(err);
        if(err.status === 401) {
          const {errors} = err.error;
          if(errors) {
            this.error = errors[0];
          } else {
            this.error = "invalid email or password";
          }
          return;
        }
      }
    );
  }

}
