import { AccountService } from './../account.service';
import { FormGroup, FormControl } from '@angular/forms';
import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'cprobid-signup',
  templateUrl: './signup.component.html',
  styleUrls: ['./signup.component.scss']
})
export class SignupComponent implements OnInit {
  sigupForm = new FormGroup(
    {
      email: new FormControl(''),
      password: new FormControl(''),
      password_confirmation: new FormControl('')
    }
  );

  error: string;

  constructor(private account: AccountService, private router: Router) { }

  ngOnInit() {
  }

  onSubmit() {
    const {email,password,password_confirmation} = this.sigupForm.value;
    this.account.signup(email,password,password_confirmation).toPromise().then(
      () => {
        this.router.navigateByUrl('/');
      }
    ).catch(
      (err) => {
        if(err.status === 422) {
          const {error} = err;
          this.error = error.errors.full_messages[0];
          return;
        }
      }
    )
  }

}
