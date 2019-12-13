import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'cprobid-msms-experiments',
  templateUrl: './msms-experiments.component.html',
  styleUrls: ['./msms-experiments.component.scss']
})
export class MsmsExperimentsComponent implements OnInit {

  constructor(private http: HttpClient) { }

  ngOnInit() {
    this.http.get('/api/ms_ms_experiments').toPromise().then(
      (res) => {
        console.log(res);
      }
    )
  }

}
